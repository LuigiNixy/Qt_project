#include "course.h"

course::course()
{

}

course::course(string name_, int x, QTime time_,QTime endTime_,string classroom_,string teacher):courseName(name_),
    dd(x),startTime(time_),endTime(endTime_),classroom(classroom_),teacherName(teacher){

}


