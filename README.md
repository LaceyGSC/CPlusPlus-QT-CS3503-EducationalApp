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
