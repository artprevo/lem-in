# lem-in

The plan of this project is to help ants get out of a maze by the most optimized path for the whole colony.
The input is randomly generated, can have 1 ants like 100 000, and they'll have to pass through 1 to XX XXX rooms.

For lem-in the basic structure is going to be a linked-list of rooms and ants. They will be re-organized in matrices so the algorythm can be fast enough
to give a result in less than 1 or 2 seconds when too many rooms and ants are involved.

- The input have to be read from the standard entree, get_next_line will do the job.
- The parsing is quite simple, just ignore the commentaries and treat the input without any error.
- The algorythm is not inspired from any already existing algorythm. The algo run through a matrice of rooms to detect dead ends and create every possible unique path.
Then it runs through another matrice of that paths it just found to make the whole combination of path the ants can use.
- The final algorythm gives each combination a number of steps, and mixing the ants in the operation gives us the best result at the end.
- For printing, he program attributes a path to each ants, and running through the linked-list of path / room makes it easy to print on the standard output.

This project was handled alone in its majority, special thanks to @jegloff for the help on the algorythm.
