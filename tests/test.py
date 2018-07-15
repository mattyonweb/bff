import os
import subprocess as sp
import time

results = {
    "01-simple-print.bf"    : (lambda s: s==b"F"),
    "02-hello-world.bf"     : (lambda s: s==b"hello world"),
    "03-memory-size.bf"     : (lambda s: s.count(b"!") + 1),
    "04-obscure-problems.bf": (lambda s: s==b"H\n"),
    "05-reverse.bf"         : (lambda s: s==b"olleh"),
    "06-rot13.bf"           : (lambda s: s==b"uryyb"),
    "07-comments.bf"        : (lambda s: s==b"hello world"),
}

where_am_i   = os.path.abspath(__file__)
tests_folder = "/".join(where_am_i.split("/")[:-1])
binary_path  = "/".join(tests_folder.split("/")[:-1]) + "/brainfuck"

successful = 0

for fn in sorted(os.listdir(tests_folder)):
    if fn[-2:] == "py":
        continue

    print(fn, end=" --> ")

    result = sp.run([binary_path, tests_folder + "/" + fn], stdout=sp.PIPE, input=b"hello")

    if fn == "03-memory-size.bf":   # È un test lento, non è necessario il loop
        print(results[fn](result.stdout))
        successful += 1
        continue

    start = time.time()
    for i in range(1000):
        sp.run([binary_path, tests_folder + "/" + fn], stdout=sp.PIPE, input=b"hello")
    end = time.time() - start
        
    try:
        print("{} - {} ms avg".format(results[fn](result.stdout), 1000* (end / 10000)))
        
        if results[fn](result.stdout):
            successful += 1
    except:
        print("Test non specificato dentro il file python.")

print("\nPercentage of success: {}%!".format(int(100*successful/(len(os.listdir(tests_folder))-1))))
    
