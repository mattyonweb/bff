import os
import subprocess as sp

results = {
    "01-simple-print.bf"    : (lambda s: s==b"F"),
    "02-hello-world.bf"     : (lambda s: s==b"hello world"),
    "03-memory-size.bf"     : (lambda s: s.count(b"!") + 1),
    "04-obscure-problems.bf": (lambda s: s==b"H\n"),
    "05-reverse.bf"         : (lambda s: s==b"otanacoid"),
    "06-rot13.bf"           : (lambda s: s==b"uryyb")
}

successful = 0

for fn in sorted(os.listdir("tests")):
    print(fn, end=" --> ")

    if (fn == "05-reverse.bf"):
        result = sp.run(["./brainfuck", "tests/" + fn], stdout=sp.PIPE,
                        input=b"diocanato")
    elif (fn == "06-rot13.bf"):
        result = sp.run(["./brainfuck", "tests/" + fn], stdout=sp.PIPE,
                        input=b"hello")
    else:
        result = sp.run(["./brainfuck", "tests/" + fn], stdout=sp.PIPE)

    try:
        print(results[fn](result.stdout))
        
        if results[fn](result.stdout):
            successful += 1
    except:
        print("Test non specificato dentro il file python.")

print("\nPercentage of success: {}%!".format(100*int(successful/len(os.listdir("tests")))))
    
