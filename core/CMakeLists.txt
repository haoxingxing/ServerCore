cmake_minimum_required (VERSION 3.8)

aux_source_directory(. src)
add_executable (StarCore ${src})
set_target_properties(StarCore PROPERTIES DEBUG_POSTFIX "d") 
set_target_properties(StarCore PROPERTIES OUTPUT_NAME "StarCore.${FILENAME_SUFFIX}")
if (UNIX)
	TARGET_LINK_LIBRARIES(StarCore dl)
endif()
link_directories(${OUTDIR})

