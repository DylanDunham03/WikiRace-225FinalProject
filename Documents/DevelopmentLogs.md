# Development Logs
<p align="center">
  <a href="#week-1">Week 1</a> •
  <a href="#week-2">Week 2</a> •
  <a href="#week-3">Week 3</a> •
  <a href="#week-4">Week 4</a>
</p>

## Week 1

### Weekly Goals
For this week our group only goals was to figure out our project plan, fill in the project proposal and also finish setting up the github repo and outing Sahil our mentor to it as well. We met on thursday from 4:30 - 6:30 to do this as was mentioned in the team goals portion of this project paper. Since this was the first week not much concrete work was done other than setting up

### Specific Tasks Completed (and by who)
So basically Dylan, Rachanon (Andrew), and Chris worked on the project proposal parts 1, 2, 3, and 4. We all sat in a room together working on the project proposal and after we finished those parts those three guys worked on writing everything down and Shubham's job was to complete the development log to dicuss and reiterate everything we all did.

### Problems Encountered 
I guess we were having some difficulty understand how to apply the algorithms that we selected to the actual project. For our project since we are doing wikepedia hyperlinks we know that we want to use some sort of strong connected component algorithm however we realized that the time it may take to run over a million nodes might take a lot of time so we were just discussing how we can chop of the data to make the program run more efficiently.

### Plans for next week
For this week our plan is to start coding have a basic setup of all the function we need to write along with proper documentation of what all of our functions are going to do including its helpers.

### Optional: Questions for mentor
How would you recommend parsing very large .txt files > ~1.8 Million lines.

## Week 2

### Weekly Goals
So this week we had 3 goals
1. Fix the project proposal because we needed to add weights to our graph.
2. Set up the project in the CS225 docker, add the proper CMake files so that we can the run the code, set up files to add code in(wikirace.cpp and wikirace.h), import in our data from the zip files
3. Modify the constructor for the weights, and finish the Strongly connected components part of the project. 

### Specific Tasks Completed (and by who)

Task 1) was completed by everyone in the group we all met at grainger on thursdya November 10th and then on sunday November 6th and finished the project proposal. 

Task 2) we all also sat together on those days to set up the github, make sure the github was linked to all our VSCodes and make sure we are able to do basic functionality like git pull, git commit to our own branches and just set up the .h files as well

Task 3) Chris finished the strongly connected component part of his code and it is working because he also wrote test cases for them to check. Dylan modified the constructor changing the private variable of the adjaceny map to contain the weight of each outgoing edge.

### Problems Encountered 
Not really any problems as of right now, we are just still in the pondering phase of how to write some of the algorithms but we aren't stuck anywhere at the moment, although this might change.

### Plans for next week
Not really any like set plans right now we will figure those out on sunday November 13th and those plans will exceed through break but we think we can have the main code for the project done by the end of thanksgiving break. but for now we need to spend some time working on the BFS algorithm function that checks if there is an existing path from the two input links and return true or false which will be my part to work on (Shubham) and then Andrew will work on the Dikshtra path to find the shortest path.

### Optional: Questions for mentor
Our main data is so big and because of that we cant really push that data file to github because it exceeds the 25 MB limit for a file is there any way that we can get around this Sahil?

## Week 3

### Weekly Goals
For this week our team had two big goals. The first one was to complete test cases for our small and medium datasets for Dkistras shorted path algorithm which Andrew was able to accomplish. The second goal was the complete the BFS Algorithm and write test cases for the small and medium data files which was completed by myself(Shubham). Our last goal was to finish the Mid Project check in and test all the code to make sure everything was working before the check in.

### Specific Tasks Completed (and by who)
Andrew wrote tests cases for Djkitras Method and completed writing the algorithm code. Shubham wrote test cases for small and medium data files and completed writing algorithm code for BFS. We all participated in the mid project check in. Goals for the week were met.

### Problems Encountered 
We just still aren't sure if we are going to try to compress the dataset and put it into github to meet the 25 MB size limit, or if we are going to use google drive or some other option. Our team will figure this out on Sunday when we meet again.

### Plans for next week
Our plan is to complete the entire project from top to bottom and create the video over a zoom call for the submission over Fall Break. I would say right now we are 85% done with the project, all of the C++ algorithmic coding is complete we just have some technical issues that we need to take care of with moving our big data file into github or into a google drive whichever one our team decides and we also have to write testcases against the actual data set not just the ones we have been making up which are smaller and more or less comprehensive.

### Optional: Questions for mentor

## Week 4

### Weekly Goals
For this week, the main goal of our team is to complete all of the Final Deliverables. We divided the work into sections: Code for Interactive Questions when the user run the program, Running Instructions, GitHub organization, Report, Leading Question, Presentation, Presentation Video Recording, and Demo Video Recording. All of the above were accomplished by our members listed in the next question, and we have finished everything for this project.

### Specific Tasks Completed (and by who)
1. Code for Interactive Questions when the user run the program: Andrew
2, Running Instructions: Andrew (write) and Chris (double-checked by starting from cloning the project again)
3. GitHub organization: Shubham and Dylan
4. Report: Dylan (main), and each member also write about their own algorithms
5. Leading Question: Shubham 
6. Presentation: all members responsible for their parts
7. Presentation Video Recording: all members, with Dylan looking over the logistics
8. Demo Video Recording: Andrew
Goals for the week were met.

### Problems Encountered 
At first, we're not sure if we can change our Kosaraju algorithm to iterative implementation or not, since our recursive version encounters Stack Overflow problem when the data set is too big. We contacted our mentor and he said that cutting the data set and showing that it works on smaller-sized datasets is fine (not too small). Therefore, we decided to go by this solution, and explain it in our Final Deliverables.

### Plans for next week
None since we finished our project.

### Optional: Questions for mentor
From our understanding, we just have to upload everything to GitHub, and then we're done right?
