include(usercore.pri)

SOURCES     +=  \
                src/usercore.cpp \
                src/core/abstract_robot_item.cpp \
                src/core/abstract_robot_item_p.cpp \
                src/core/stream.cpp \
                src/core/stream_base.cpp \
                src/core/stream_to_input_mapper.cpp \
                src/gui/config_dialog.cpp \
                src/gui/dock_widget_signaling.cpp \
                src/gui/image_widget.cpp \
                src/gui/shared_window.cpp \
                src/gui/slider_label.cpp \
                src/portable/input_queue.cpp \
                src/portable/message.cpp \
                src/portable/message_m.cpp \
                src/portable/message_p.cpp \
                src/portable/portable_image.cpp \
                src/portable/portable_image_m.cpp \
                src/portable/portable_image_p.cpp \
                src/portable/portable_item.cpp \
                src/portable/portable_item_p.cpp \
                src/portable/stream_object.cpp \
                src/portable/stream_object_p.cpp \
                src/portable/template_decl.cpp

HEADERS     +=  \
                include/usercore.h \
                include/core/abstract_robot_item.h \
                include/core/abstract_robot_item_p.h \
                include/core/robot_core.h \
                include/core/stream.h \
                include/core/stream_base.h \
                include/core/stream_to_input_mapper.h \
                include/gui/config_dialog.h \
                include/gui/dock_widget_signaling.h \
                include/gui/image_widget.h \
                include/gui/shared_window.h \
                include/gui/slider_label.h \
                include/portable/input_queue.h \
                include/portable/message.h \
                include/portable/message_m.h \
                include/portable/message_p.h \
                include/portable/portable_image.h \
                include/portable/portable_image_m.h \
                include/portable/portable_image_p.h \
                include/portable/portable_item.h \
                include/portable/portable_item_global.h \
                include/portable/portable_item_p.h \
                include/portable/stream_object.h \
                include/portable/stream_object_p.h \
                include/portable/strong_typedef.h \
                include/portable/template_decl.h \
    include/portable/all_streams.h

RESOURCES   +=  resources.qrc
LIBS        += -lopencv_core
