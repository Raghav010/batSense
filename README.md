## **batSense**

### **What this is**
This is a program which designs and outputs an FSA(Finite State Automaton) that tries to beat an opponent FSA, which plays Rock-Paper-Scissors (RPS) with an unknown initial state, in as many rounds as possible. 

The program designs a FSA that tries to achieve this by probing the opponent FSA to find the state the opponent FSA is in currently, at the cost of losing a few rounds. Once the FSA figures out which state the opponent FSA is at, it stays one step ahead of the opponent FSA effectively beating it.

### **Performance**
Given the opponent’s FSA with n ≤ 30 states but not its initial state. Program outputs an FSA with m ≤ 1000 states and a fixed initial state such that it beats the opponent FSA as many times as possible. 10,000 rounds simulated for each possible initial state of the opponent FSA.
<br>
<br>
This program has an Average Score of 99.70


**Input Format**
![Input Format](/media/inputformat.png)
![Sample input format](/media/sampleInputFormat.png)
Output format is similar
