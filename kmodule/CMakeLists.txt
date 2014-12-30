set(kofile ${CMAKE_CURRENT_SOURCE_DIR}/cdev_driver.ko)
set(KERNEL_BUILD_DIR /lib/modules/${CMAKE_SYSTEM_VERSION}/build)
set(KBUILD_CMD ${CMAKE_MAKE_PROGRAM}
        -C ${KERNEL_BUILD_DIR}
        M=${CMAKE_CURRENT_SOURCE_DIR} modules)


add_custom_command(OUTPUT ${kofile}
                                         COMMAND ${KBUILD_CMD}
                                         DEPENDS cdev_driver.c kbuild
                                         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                                         COMMENT "Building udpc.ko"
                                         )

add_custom_target(cdev_driver ALL DEPENDS ${kofile})