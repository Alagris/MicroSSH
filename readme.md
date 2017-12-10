How to compile:
- compile server
```make server```
- compile client
```make client```
- compile rsa key generator
```make rsagen```

How to run any of these:
- ```./run.sh rsagen```
- ```./run.sh client```
- ```./run.sh server```

(commandline parameters are scpecified inside `run.sh` script)
Before you start server or client make sure that you've got RSA keys generated and stored in your working directory. If you clone the repo you will have those already, but you can of course generate a new pair if you wish.

Once you've got server up and running and you manage to connect to it with a client yo ucan start working on a turing machine. The syntax is just like in brainfuck (but without loops and input):
- \+ increments value at current position
- \- decrements value at current position
- \< moves once cell left
- \> moves once cell right
- \. displays content of current cell
