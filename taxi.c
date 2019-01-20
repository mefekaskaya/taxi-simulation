#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

//Prepared by Mehmet Efe Kaşkaya - 


//There is segmentation fault at the end but except that, everything works properly
//All taxis take four students respectively, no starvation
//Taxis distributes students and come back to take waiting ones

// The maximum number of student threads.
#define MAX_STUDENTS 100
#define TAXI 10

// Function prototypes…
void *student(void *num);
void *driver(void *num);

void randwait();

// Define the semaphores.


// driverChair ensures mutually exclusive access to
// the driver chair.
sem_t driverChair;

// driverPillow is used to allow the driver to sleep
// until a student arrives.
sem_t driverPillow;

// Flag to stop the driver thread when all students
// have been serviced.
int allDone = 0;

int main(int argc, char *argv[])
{
    pthread_t dtid[TAXI];
    pthread_t tid[MAX_STUDENTS];
    int i, numStudents;
    int numSeats=4;
    int Number_taxi[TAXI], Number_student[MAX_STUDENTS];

    printf("Enter the number of Students : ");
    scanf("%d", &numStudents);
    

    // Make sure the number of threads is less than the number of
    // students we can support.
    if (numStudents > MAX_STUDENTS)
    {
        printf("The maximum number of Students is %d.\n", MAX_STUDENTS);
        exit(-1);
    }

    // Initialize the numbers array.
    for (i = 1; i <= MAX_STUDENTS; i++)
    {
        Number_student[i] = i;
    }

    for (i = 1; i <= TAXI; i++)
    {
        Number_taxi[i] = i;
    }

    // Initialize the semaphores with initial values…
    sem_init(&driverChair, 0, 1);
    sem_init(&driverPillow, 0, 0);

    int x = 1;//The number of students to spin the tour until loop terminates
    while (x <= numStudents)
    {
        
        
        
        int j, k, m;
        for (j = 1; j <= TAXI; j++)
        {
            //x is assigned to k at first to assign student numbers respectively 
            //loop spins for four times increasing to make four students got in taxis
            for (k = x; k <= x + 3; k++)
            {
                pthread_create(&tid[k], NULL, student, (void *)&Number_student[k]);
                randwait();
            }
            
            for (m = x; m <= x + 3; m++)
            {
                pthread_join(tid[m], NULL);
                randwait();
            }
            /*The student's getting in and out of taxi printf's were shown
            in the main and not in the thread functions
            because the values assigned to the
            student and the values assigned 
            to the taxi cannot be taken 
            in once in the thread functions.*/

            
            printf("Taxi %d takes students %d, %d, %d and %d\n", j, x, x + 1, x + 2, x + 3);
            pthread_create(&dtid, NULL, driver, (void *)&Number_taxi[j]);
            printf("Student %d, %d, %d and %d are leaving the %d. taxi\n", x, x + 1, x + 2, x + 3, j);
            x = x + 4;
            
            
            //four is added to x when each four students created,
            //to provide an order in students number 


            randwait();
            if(x==100 && !allDone)//this 'if' provides last four students to get in the taxi
            {
                pthread_create(&dtid, NULL, driver, (void *)&Number_taxi[j]);
                printf("Student %d, %d, %d and %d are leaving the %d. taxi\n", x, x + 1, x + 2, x + 3, j);
            }

            
            //this 'if' provides last 5 taxis not to work
            //because for last 20 students, only 5 taxis are necessary
            if(x > numStudents)
            {
                j = TAXI;
                break;
            }
            
            

        }    
    }
    int n;
    for (n = 1; n <= TAXI; n++)
    {
        pthread_join(dtid[n], NULL);
        randwait();
    }
    return 0;
}

void *student(void *number)
{
    int num = *(int *)number;

    // Leave for the school and take some random amount of
    // time to arrive.
    printf("Student %d leaving for school.\n", num);
    printf("Student %d arrived at hitchhiking area.\n", num);



    // Wake up the driver or wait for being taxi full…
    if(num % 4 == 1)
    {
        sem_post(&driverPillow);
        printf("Student %d waking the driver.\n", num);
        sem_wait(&driverChair);
    }
    
    else
    {
        int remaining_student = 4 - (num % 4);
        printf("last %d student, let's go\n", remaining_student);
    }
    
}

void *driver(void *number)
{
    int num = *(int *)number;
    // While there are still students to be serviced…
    // Our driver is omnicient and can tell if there are
    // students still on the way to his school.
    while (!allDone)
    {

        // Sleep until someone arrives and wakes you..
        // Skip this stuff at the end…
        if (!allDone)
        {
            // Take a random amount of time to distribute the
            // student’s
            printf("The driver %d is distributing students\n", num);
            randwait();
            printf("The driver %d has finished distributing.\n", num);
            sem_wait(&driverPillow);
            printf("The driver %d is sleeping\n", num);
            sem_post(&driverChair);
            
        }
        else
        {
            printf("The driver %d is going home for the day.\n", num);
        }
    }
}

void randwait()
{
    int len;
    srand(time(NULL)); 
    len = rand() % 5;
    sleep(len);
}
