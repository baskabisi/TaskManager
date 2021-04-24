# Task Manager

This is a console application running some jobs in parallel.
Max number of jobs to be run in parallel depends on the platform and is not possible to exceed.

User is asked to enter the number of jobs to run.
"Please enter number of jobs to run:"
Only numbers not above the max number of jobs are accepted.

After a valid number is provided, user is asked to enter commands.

Valid commands are:
o status – returns ids and status of all registered jobs.
           The job status can be one of the following: idle/running/paused/aborted
o start <id> - starts job with the given id
o abort <id> - aborts execution of a job with the given id
o pause <id> - halts execution of a job with the given id
o resume <id> - resumes execution of a halted job
o quit – aborts all running jobs and quits the application
  
User is asked to enter a command until a valid command is provided in a valid format.
See that commands except for 'status' and 'quit' requires valid job id's.
