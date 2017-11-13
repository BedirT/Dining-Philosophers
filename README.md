# Dining-Philosophers
My Presentation For OS class | Topic: Simulation for Dining Philosophers

**Task:** Simulate the Dining Philosophers problem, demonstrate three cases, explain how did they happen:
1. Deadlock
2. Starvation
3. Without any problem

## Presentation
Here I will attach my presentation. Nothing fancy :) but it worked proparly. I will include couple versions, I used Keynote so there might be couple probelms with other version:
- [Keynote](Presentations/DPhilosophers.key)
- [PDF](Presentations/DPhilosophers.pdf)
- [Pptx](Presentations/DPhilosophers.pptx)
- [Images](Presentations/DPhilosophers/)

## Simulation
My code present is not an advanced one, and might have some mistakes. I commented everything that I tried to include, so it should be easy to understand what did I do, and why. Feel free to contribute. Here I will explain what needs to be done to demonstrate each case in the code that I have. You can find the code [here](DiningPhilosophers.cpp)

### Deadlock
---
For creating a deadlock we need to change couple lines:
- Comment out lines 37 to 41
- Make sure that rIndex and lIndex are using lines 59-60

This will create a deadlock, cause everyone will pick up the fork that on their left side... And since you removed dropping the fork part they will get stuck.

### Starvation
---
For creating Starvation, same thing, we will change couple lines:
- Comment out lines 37 to 41
- Make sure that rIndex and lIndex are using lines 61-62
- Make sure the sleep_for 's are commented out. So lines: 21, 70 are commented out.

This will create a Starvation hopefully :). Since we have indexes(forks) fixed but still have stubborn philosophers(will not put the fork back till he/she eats). And there is no waiting time so they will keep trying to eat, without letting others get the fork.

### Normal
---
For normal situation, the code itself is in this position right now, but still.. let me explain:
- Make sure that lines 37 to 41 are not commented out.
- Make sure that rIndex and lIndex are using lines 61-62
- Make sure the sleep_for 's are NOT commented out.

First bullet is because we will have open-minded philosophers, and if they cannot eat they will let others do so... I already explained rIndex, lIndex situation in Deadlock. Lastly sleep_for's will let philosophers wait before trying to eat right after finishing eating.

#### References
- https://github.com/NAUniversity/AlgorithmsBook/blob/master/Chapter%2018%20-%20Distributed%20Algorithms.ipynb
- https://en.wikipedia.org/wiki/Dining_philosophers_problem
- https://www.youtube.com/watch?v=p0SKPpC5r9U 
