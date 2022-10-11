//
// Created by Luca Brignone on 06/10/22.
//

#ifndef PROGETTO_ERRORHANDLING_H
#define PROGETTO_ERRORHANDLING_H

#include <exception>
#include <limits>

typedef enum {ERR_arguments_number, ERR_file_name, ERR_open_file, ERR_empty_file, ERR_empty_field, ERR_file_format, ERR_student_format,
              ERR_professor_format, ERR_classroom_format, ERR_course_format, ERR_hour_set, ERR_string_identifier, ERR_academic_year,
              ERR_date_field_conversion, ERR_date_format, ERR_exceeding_session_dates, ERR_inverted_dates, ERR_exceeding_session_number,
              ERR_session_planning, ERR_session_duration, ERR_cfu_field, ERR_course_status, ERR_parallel_course_number, ERR_exam_duration,
              ERR_stoi_conversion, ERR_entrance_time, ERR_exit_time, ERR_exam_type, ERR_classroom_type, ERR_partecipants,
              ERR_id_field, ERR_missing_professor, ERR_date_overlap, ERR_professor_changed, ERR_update_database, ERR_wrong_identifier,
              ERR_missing_field, ERR_parallel_course_number_inherit, ERR_separator, OK = std::numeric_limits<unsigned int>::max()} t_errorCodes;

class isNotMain : public std::exception {
private:
    const char* message;
public:
    isNotMain();
    const char* what() const noexcept;
};

#endif //PROGETTO_ERRORHANDLING_H
