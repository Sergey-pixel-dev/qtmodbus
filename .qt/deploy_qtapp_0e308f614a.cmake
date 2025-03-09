include(/home/serg50012/LIM/modbus/qtapp/.qt/QtDeploySupport.cmake)
include("${CMAKE_CURRENT_LIST_DIR}/qtapp-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE /home/serg50012/LIM/modbus/qtapp/qtapp
    GENERATE_QT_CONF
)
