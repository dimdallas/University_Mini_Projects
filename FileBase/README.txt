FileBase.c is a program for 
creating and managing custom database-like files.
These databases can import various file types.
The point is to store many files simultaneously in a single database file.

Function overview:
Import file
   * By pressing "1" and typing the filename or the filepath.
   * If two filepaths ends up in the same filename, it will assume it is
   * the same file, thus asking you to replace it.
Search file
   * By pressing "2" and typing part of the filename.
   * A list of files containing this part is printed.
Export file
   * By pressing "3" and typing filename existing in database.
   * The program asks you to type the filename for the exported file.
   * A new file is being created with the specified filename.
   * Note: You are responsible for assigning correct file extension.
Delete file
   * By pressing "4" and typing filename existing in database.
