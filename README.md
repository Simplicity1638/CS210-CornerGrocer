# CS210-CornerGrocer
C++ frequency analysis program that reads and writes to file with an option menu

This project reads groacery data from a file (FoodList.txt) and calculates how many times they appear. It uses a map to store the names and frequency of these items, writes it to a backup file, and also gives a menu option which allows the user to search specific items, see all frequencies, or display a histogram. 

What I think I did well was keeping it as organized as possible. I tried to avoid cluttering up the main function and instead used seperate functions for file handling, menu control, input validation, and output formatting. I also implimented proper input validation to prevent blank searches and invalid menu selections. One improvement I think I would make is possibly making the search function not case sensitive so users don't have to type exactly what they are searching for. I could also allow the user to input their own file so it is more versatile for everyone.

The most difficult part was using the "map" container with file input to make sure that everything was counted correctly. I also was using an older C++ program that wasn't updated so parts of this program I had to code differently than I had been taught. I overcame these problems/challenges by testing constantly and checking how the map updated the values when the files were being read. 

The most transferrable skills in this project is file input/output, input validation, STL containers, and keeping code readable/maintainable. I made this program maintainable by seperating the functions out of main() and using a class to encapsulate data. I also avoided using global variables plus added comments to explain what each bit of code does. The way that this program is structured makes it easier to update in the future either with new options in the menu or changing file formats. 
