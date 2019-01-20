# taxi-simulation
Each taxi has 4 students capacity.
 Students will come to taxi-stop continuously and
random periods.
 The taxi stop has 10 taxis and also 10 taxi
drivers. Also each taxi contains one taxi driver.
 The states for each taxi:
 Collect student state: Driver will announce to
the students his remaining places to get in
the taxi, if it has one or more students in the
taxi. For example, each taxi has 2 students
and wait two more students, driver call “The
last two students, let's get up!”
 Full and transport state: If there are 4
students in the taxi, the taxi will leave from
the taxi stop.
The states for each student:
 Waiting in taxi: When a student comes at
stop, she/he gets in the nearly full capacity
taxi. If no student in taxi, first student wakes
driver if he is sleeping. And the students will
study or relax in the taxi until the taxi's full.
 Waiting at taxi stop: If there is no taxi at the
taxi stop, she/he's gonna wait for a taxi at
the stop.
Starvation was taken to consideration.
