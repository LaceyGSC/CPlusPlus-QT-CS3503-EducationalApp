# Important Things to Note
	1. Read the code style guide below.
	
	2. Create an issue detailing the event leading up to a segmentation fault if you find one.
	
	3. Please ensure that your code conforms to the code style guide before committing.
	
	4. DO NOT MERGE WITH THE MASTER BRANCH if your current commit does not build/run.

# Code Style Guide
	1. Identifiers should be named using the camel-case convention.
		a. Class and file names should begin with an upper case.
			E.g.: "MyCanvas.cpp",
				  "class MyCanvas {...};"
		b. Method and variable names should begin with a lower case.
			E.g.: "void myMethod()",
				  "int numOfPlants"
			
	2. Constant identifiers should be named with all letters capitalized and underscores for spaces.
		E.g.: "const int FRAME_RATE = 1./60.f"
		
	3. Member variables in a class will be declared with a lowercase m appended to the variable name.
		E.g.: "int mLineNumber"
	
	4. In a header file, class methods should be declared first followed by class variables.
		E.g.: "class MyCanvas
			   {
			   public:
			       MyCanvas(int lines, bool active);
				   ~MyCanvas();
			   private:
			       static const int FRAME_RATE;
				   int mLines;
				   bool mActive;
			   };"
	
	5. Header files should only contain declarations.
	
	6. Class methods that are not obvious by their name should be commented.
	
	7. Source files should include the name of the author(s) at the beginning of the file.
	
	8. A tab should contain 4 spaces.
	
	9. The opening curly brace should be placed on a new line.
		E.g.: "void myMethod()
			   {
			   }"
	
	10. Constructors in .cpp files should be written as follows:
		"MyCanvas::MyCanvas(int lines, bool active)
			: mLineNumber(lines)
			, mActive(active)
		 {
		 	// Do something
		 }"

# Other Useful Stuff
	1. Try to minimize the use of pointers. Only use pointers if the object created needs to be kept alive beyond
	   the current scope.
	   
	2. Use std::unique_ptr<type> (located in <memory>) as a replacement of naked pointers if you do not want to
	   manage the memory manually (meaning, no need to delete with std::unique_ptr). std::unique_ptr works the
	   same way as naked pointers.
		E.g.: Naked pointer: "int *p = 10",
		      std::unique_ptr: "std::unique_ptr<int> p = 10"
		      Dereferencing is the same for both: "std::cout << *p"
		      
	3. ALWAYS check if a pointer is nullptr before dereferencing (it will help to avoid seg fault):
		E.g.: "if (p != nullptr) { // Do something }"
		
	4. It might be a good idea to use std::move if you no longer want to use an STL container but want to copy
	   the data out.
		E.g.: "CustomClass returnMethod()
		       {
		           CustomClass obj(...);
			   
			   // This moves the data from obj into the copy of the CustomClass to be returned.
			   // This means that no deep copies were performed.
		           return std::move(obj);
		       }"
		       Note: You need a move constructor for std::move to work on custom classes. AFAIK, all STL
		       containers have move constructor and therefore, can be used with std::move.
	
	5. About const with member functions:
	
		a. const int someMethod() // Returned value cannot be changed
		- Useful if you want to return something that you do not want to be changed.
		- E.g.: "const Frame& getFrame()"
		- Note: This should probably be "const Frame& getFrame() const". See (c).
		
		b. void someMethod(const int num) // Passed value cannot be changed
		- Useful if you want to ensure arguments passed to the function shall not be changed.
		- E.g.: "void print(const Point& point1)"
		
		c. void someMethod() const // Method does not modify the object
		- Useful if you want to ensure that the method does not modify the object (read-only). (Normally,
		  this is true for accessor/get functions)
		- E.g.: "Point getPoint() const"
		
	   Please use const appropriately when writing member functions because not only does it help with readability,
	   it prevents seg faults by restraining the ability to change variables that are not meant to be changed or are
	   assumed to be unalterable.
		
	6. If you have any other useful tips, share it here!
