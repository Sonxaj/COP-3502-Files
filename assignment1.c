#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR_LEN 20 //for names


//structs

typedef struct student{
    int id;
    char *lname;//last name
    float *scores;//scores of student. size taken from num_scores array
    float std_avg;//avg score of student (to be calculated)
}student;

typedef struct course{
    char *course_name;//course name
    int num_sections;//number of sections

    //stores array of student arrays(2D). size is num_sections
    student **sections;

    //stores array of num of students in each section. size is num_sections
    int *num_students;

    //stores array of num of assignments in each section. size is num_sections
    int *num_scores;
}course;




//functions

/*
    There are 2 versions of each function:
    one for the courses array, and one for the section array
    inside each index of the courses array.
*/

//allocates memory for all courses of a given test case
course *read_courses(FILE *fp, int *num_courses);


//called inside read_courses function
//returns address of the 2D array used for storing student data per section
student **read_sections(FILE *fp,
                        int num_students[],
                        int num_scores[],
                        int num_sections);



//prints data to console
void process_courses(course *courses, int num_courses);




//actually does most of the printing; similar parameters as read_sections
void data_print(student **sections,
                int num_students[],
                int num_scores[],
                int num_sections);



//frees up all used memory for courses
void release_courses(course *courses, int num_courses);


//frees up all used memory for sections; called inside release_courses
void release_sections(student **sections,
                      int num_sections,
                      int *num_students,
                      int *num_scores);







//hi, welcome to main! enjoy your visit!
int main(void){

    FILE *fp = fopen("assignment1input.txt", "r"); //open txt for reading

    int numTestCases;  //number of test cases

    course *courses; //used for array of courses


    fscanf(fp, "%d", &numTestCases);  //grab num of test cases

    //for each test case
    for(int i=0; i<numTestCases; i++){

        int numCourses; //number of courses

        fscanf(fp, "%d", &numCourses);

        //present current test case
        printf("Test Case: %d\n", i+1);


        //read
        courses = read_courses(fp, &numCourses);


        //process
        process_courses(courses, numCourses);


        //free memory
        release_courses(courses, numCourses);


        printf("\n");

    }

    fclose(fp); //done
}







//functions

course *read_courses(FILE *fp, int *num_courses){

    fscanf(fp, "%d", num_courses);  //grab num of test cases


    //allocate mem
    course *crs = (course*)malloc(sizeof(course)* *num_courses);


    char word[MAX_STR_LEN]; //for storing strings


    for(int i=0; i<*num_courses; i++){

        fscanf(fp, "%s", word); //copy name of course


        //allocate mem for that string; +1 for "\0"
        crs[i].course_name = malloc(strlen(word)+1);


        strcpy(crs[i].course_name, word); //then copy name inside


        //read num of sections
        fscanf(fp, "%d", &crs[i].num_sections);


        //allocate mem for num of students
        crs[i].num_students = (int*)malloc(sizeof(int)*crs[i].num_sections);


        //allocate mem for num of assignments
        crs[i].num_scores = (int*)malloc(sizeof(int)*crs[i].num_sections);


        //call read sections here
        crs[i].sections = read_sections(fp,
                                        crs[i].num_students,
                                        crs[i].num_scores,
                                        crs[i].num_sections);

    }
    return crs;
}




student **read_sections(FILE *fp,
                        int num_students[],
                        int num_scores[],
                        int num_sections){

    //allocate mem for a temporary student 2D array used for copying data
    student **sec = (student**)malloc(sizeof(student*)*num_sections);


    //for storing names
    char lname[MAX_STR_LEN];

    for(int i=0; i<num_sections; i++){

        //read number of students and assignments, then store them
        fscanf(fp, "%d %d", &num_students[i], &num_scores[i]);


        //allocate mem for those students
        sec[i] = (student*)malloc(sizeof(student)*num_students[i]);

        for(int j=0; j<num_students[i]; j++){


            //read and store the id num and name
            fscanf(fp, "%d %s", &sec[i][j].id, lname);


            //allocate memory for name
            sec[i][j].lname = malloc(strlen(lname)+1);


            //copy into array
            strcpy(sec[i][j].lname, lname);


            //allocate mem for scores
            sec[i][j].scores = (float*)malloc(sizeof(float)*num_scores[i]);

            float sum = 0.0; //for calculating avg

            for(int k=0; k<num_scores[i]; k++){

                //read the student's scores
                fscanf(fp, "%f", &sec[i][j].scores[k]);

                //sum them
                sum += sec[i][j].scores[k];
            }

            //calculate avg
            sec[i][j].std_avg = sum/num_scores[i];
        }

    }
    return sec;
}





void process_courses(course *courses, int num_courses){

    for(int i=0; i<num_courses; i++){

        //first print name
        printf("%s ", courses[i].course_name);


        //now print data
        data_print(courses[i].sections,
                   courses[i].num_students,
                   courses[i].num_scores,
                   courses[i].num_sections);
    }
}





void data_print(student **sections,
                int num_students[],
                int num_scores[],
                int num_sections){


    //needed to store section avg after calculating the num of passing students
    float *s_avg = (float*)malloc(num_sections*sizeof(float));



    //for calculating "highest" things
    int highest_student=0;

    int highest_section=0;

    int passing_students=0;

    float highest_avg = 0.0;

    for(int i=0; i<num_sections; i++){


    //used for calculating the sum of the avg of the current section
    //set to 0 for loop
    float current_sum_sectionAVG = 0.0;

        for(int j=0; j<num_students[i]; j++){


            //assuming student's avg score is greater than 70 (inclusive)
            if(sections[i][j].std_avg >= 70.0){


                //increment current total of passing students
                passing_students++;
            }

            //sum to total avg's
            current_sum_sectionAVG += sections[i][j].std_avg;

            if(sections[i][j].std_avg > highest_avg){

                //update current highest

                highest_avg = sections[i][j].std_avg; //student avg

                highest_section = i; //student section

                highest_student = j; //student's current position in array
            }
        }

        //section's avg
        s_avg[i] = current_sum_sectionAVG/num_students[i];
    }

    printf("%d", passing_students); //number of students that passed

    for(int i=0; i<num_sections; i++){

        //current section avg rounded to nearest hundredth
        printf(" %.2f", s_avg[i]);
    }


    //highest student's id, name, and avg
    printf(" %d %s %.2f\n",
           sections[highest_section][highest_student].id,
           sections[highest_section][highest_student].lname,
           sections[highest_section][highest_student].std_avg);


    //clean up s_avg since no longer needed
    free(s_avg);
}





void release_courses(course *courses, int num_courses){

    for(int i=0; i<num_courses; i++){

        //free the name
        free(courses[i].course_name);

        //free the sections
        release_sections(courses[i].sections,
                         courses[i].num_sections,
                         courses[i].num_students,
                         courses[i].num_scores);

        //free the number of students
        free(courses[i].num_students);

        //free the scores array
        free(courses[i].num_scores);
    }

    //now free up the courses array itself
    free(courses);
}





void release_sections(student **sections,
                      int num_sections,
                      int *num_students,
                      int *num_scores){

    for(int i=0; i<num_sections; i++){

        for(int j=0; j<num_students[i]; j++){

            //free names and scores

            free(sections[i][j].lname);
            free(sections[i][j].scores);
        }
        //free current section
        free(sections[i]);
    }

    //free the entire area of mem for section
    free(sections);
}
