cmake_minimum_required (VERSION 3.8)

aux_source_directory(. src)
aux_source_directory(./builtin src_builtin)
add_executable (StarCore ${src} ${src_builtin})
set_target_properties(StarCore PROPERTIES DEBUG_POSTFIX "d") 
set_target_properties(StarCore PROPERTIES OUTPUT_NAME "StarCore.${FILENAME_SUFFIX}")
if (UNIX)
	TARGET_LINK_LIBRARIES(StarCore dl)
endif()
link_directories(${OUTDIR})

