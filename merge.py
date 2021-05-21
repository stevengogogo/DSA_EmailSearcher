"""
Reference: 
1. https://pythonexamples.org/python-replace-string-in-file/
"""

import sys 

def remove_api_header(fn):
    replaceText(fn, 
                "#include \"api.h\"", 
                "//#include \"api.h\"")
def putback_api_header(fn):
    replaceText(fn, 
                "//#include \"api.h\"",
                "#include \"api.h\"", )

def replaceText(fn, origin, replaced):
    #read input file
    fin = open(fn, "rt")
    #read file contents to string
    data = fin.read()

    # Testing: Existence of the text
    if data.find(origin) != -1:
        print(fn + ": " +origin + " is raplaced with " + replaced )
    else:
        raise TypeError(origin + " not found")

    #replace all occurrences of the required string
    data = data.replace(origin, replaced)
    
    #close the input file
    fin.close()
    #open the input file in write mode
    fin = open(fn, "wt")
    #overrite the input file with the resulting data
    fin.write(data)
    #close the file
    fin.close()



def main():
        args = sys.argv[1:]
        if args[-1] == "remove_api":
            remove_api_header(args[0])
        elif (args[-1] == "add_api"):
            putback_api_header(args[0])
        else:
            raise TypeError("Wrong argument "+ args[-1])

if __name__ == '__main__':
    main()