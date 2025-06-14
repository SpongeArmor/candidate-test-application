
/*
* Error codes for the project
* These error codes are used to indicate the status of operations in the project.
* Each error code corresponds to a specific condition that may occur during the execution of the program.
*/
#pragma once

enum ErrorCode {
    OK,
    SENSOR_UNAVAILABLE,
    INACCURATE_SENSOR_DATA,
    INVALID_VALUE,
    INCORRECT_PARAMETERS,

    OBJECT_NOT_INITIALIZED,
    NULLPTR_EXCEPTION
};