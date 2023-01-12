//
// Created by Luca Brignone on 06/10/22.
//

#ifndef PROGETTO_ERRORHANDLING_H
#define PROGETTO_ERRORHANDLING_H

#include <exception>
#include <limits>

typedef enum {ERR_arguments_number, ERR_file_name, ERR_open_file, ERR_empty_file, ERR_empty_field, ERR_file_format, ERR_student_format,
              ERR_professor_format, ERR_classroom_format, ERR_course_format, ERR_mail_format, ERR_hour_set, ERR_string_identifier,
              ERR_academic_year, ERR_date_field_conversion, ERR_date_format, ERR_exceeding_session_dates, ERR_inverted_dates,
              ERR_exceeding_session_number, ERR_session_planning, ERR_session_duration, ERR_cfu_field, ERR_course_status,
              ERR_parallel_course_number, ERR_exam_duration, ERR_stoi_conversion, ERR_entrance_time, ERR_exit_time, ERR_exam_type,
              ERR_classroom_type, ERR_classroom_capacity, ERR_partecipants, ERR_grouped_id, ERR_parallel_course, ERR_professor_pointer,
              ERR_list_association, ERR_regular_professor, ERR_course_of_study_format, ERR_graduation_type, ERR_course_list,
              ERR_hour_incompatibility, ERR_negative_hour, ERR_hours_not_set, ERR_professor_list, ERR_professor_hour, ERR_version,
              ERR_incoherent_version_number, ERR_unavailability_format, ERR_id_field, ERR_missing_professor, ERR_date_overlap,
              ERR_professor_changed, ERR_update_database, ERR_wrong_identifier, ERR_missing_field, ERR_parallel_course_number_inherit,
              ERR_separator, ERR_other_semester, ERR_both_semester, ERR_not_found, ERR_write, ERR_missing_file, ERR_semester,
              ERR_same_course_of_study, ERR_exam_scheduling, ERR_course_not_found, OK = std::numeric_limits<unsigned int>::max()} t_errorCodes;

class isNotMain : public std::exception {
private:
    const char* message;
public:
    isNotMain();
    const char* what() const noexcept;
};

#endif //PROGETTO_ERRORHANDLING_H
