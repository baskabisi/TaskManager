# Task Manager

This is a console application running some jobs in parallel.

There are 2 types of jobs currently: 

           counting even numbers
           counting odd numbers 
  
Counting is performed with 2 secs interval and the current numbers for each jobs are displayed on the console.

User is asked to enter the number of jobs to run.
"Please enter number of jobs to run: "
Only numbers below the max number of jobs (100) are accepted.

After a valid number is provided, user is asked to enter commands.
"Please enter your command: "
Valid commands are:

           status – returns ids and status of all registered jobs.
                      The job status can be one of the following: idle/running/paused/aborted
           start <id> - starts job with the given id
           abort <id> - aborts execution of a job with the given id
           pause <id> - halts execution of a job with the given id
           resume <id> - resumes execution of a halted job
           quit – aborts all running jobs and quits the application
  
User is asked to enter a command until a valid command is provided in a valid format.
Notice that commands except 'status' and 'quit' requires valid job id's.
