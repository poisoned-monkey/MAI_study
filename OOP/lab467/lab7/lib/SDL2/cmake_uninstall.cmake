if (NOT EXISTS "/Users/nataliazavodnova/Documents/MAI_study/second_year/OOP/Labs_to_finish/oop_lab_7_FINAL/install_manifest.txt")
    message(FATAL_ERROR "Cannot find install manifest: \"/Users/nataliazavodnova/Documents/MAI_study/second_year/OOP/Labs_to_finish/oop_lab_7_FINAL/install_manifest.txt\"")
endif(NOT EXISTS "/Users/nataliazavodnova/Documents/MAI_study/second_year/OOP/Labs_to_finish/oop_lab_7_FINAL/install_manifest.txt")

file(READ "/Users/nataliazavodnova/Documents/MAI_study/second_year/OOP/Labs_to_finish/oop_lab_7_FINAL/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")
foreach (file ${files})
    message(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
    execute_process(
        COMMAND /Applications/CMake.app/Contents/bin/cmake -E remove "$ENV{DESTDIR}${file}"
        OUTPUT_VARIABLE rm_out
        RESULT_VARIABLE rm_retval
    )
    if(NOT ${rm_retval} EQUAL 0)
        message(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    endif (NOT ${rm_retval} EQUAL 0)
endforeach(file)

