# C-War-Game
In this experiment, we needed to implement a basic console game by using stack, pointers with C programming language. 
I created a Soldier class with ‘health’ and ‘strength’ attributes and I define this class attributes into ‘Stack’ by limited the size with ‘STACK_SIZE’. Whenever a Soldier enters the stack, it will be on top. If the stack is empty, it will return null value. 
I created a push method to add a soldier into the stack. Every soldier will be added from top of the stack until arriving the ‘STACK_SIZE’ count. 
I created a pop method to subtract the soldier from the stack. If the stack is already empty, it will return null value and it will print “There are no soldiers left.”. Otherwise, if there is soldiers into the stack, soldiers will be popped from top of the stack one by one.
I created a fight method which is ‘performFight’. I defined 2 variables which are attacker and defender. I entered the formula which is given in assignment description.
I created a critical shot method which is ‘performCriticalShot’. This method will pop the defender if this function is triggered in console.
In main method, I created two stacks for both sides. I used else-if to give commands and show them into the console. If Add(A) command is entered, program will ask which side? And we need to enter the side for adding the soldier. Then we need to enter the soldier datas. I couldn’t handle to add the soldiers at the same time, so I added ‘Do you want to add another soldier?’. If yes, program will redirect to the adding soldier section again. 
In reinforcement(R) section, we also need to enter side (1,2). Then it will create a soldier which has random stats. 
In fight(F) section, soldiers will attack each other when their turn come. It will print damage outputs. Whenever a soldier has 0 or below health, program will print ‘Side X has a casualty’ to show that one of the stack element has popped. And if there is no any soldier left from any side, the other side will win the war ‘Side X wins!’.
Last section is a quick way to stop executing (Q). It is quiting the application.
