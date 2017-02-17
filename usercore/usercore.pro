include(usercore.pri)

SOURCES +=  src/usercore.cpp \
            src/bases/roviz_item_dev_base.cpp \
            src/bases/roviz_item_dev_base_p.cpp \
            src/bases/stream_base.cpp \
            src/bases/stream_to_input_mapper.cpp \
            src/core/input_queue.cpp \
            src/core/roviz_item.cpp \
            src/core/template_decl.cpp \
            src/gui/config_dialog.cpp \
            src/gui/dock_widget_signaling.cpp \
            src/gui/image_widget.cpp \
            src/gui/shared_window.cpp \
            src/gui/slider_label.cpp \
            src/streams/image.cpp \
            src/streams/image_m.cpp \
            src/streams/image_p.cpp \
            src/streams/message.cpp \
            src/streams/message_m.cpp \
            src/streams/stream.cpp \
            src/streams/stream_object.cpp \
    include/config/cfg_double.cpp \
    src/config/config.cpp \
    include/config/cfg_int.cpp \
    include/config/cfg_string.cpp \
    include/config/cfg_bool.cpp \
    include/config/cfg_list.cpp \
    include/config/cfg_file_path.cpp \
    include/config/cfg_url.cpp

HEADERS +=  include/usercore.h \
            include/bases/export_handling.h \
            include/bases/roviz_item_dev_base.h \
            include/bases/roviz_item_dev_base_p.h \
            include/bases/stream_base.h \
            include/bases/stream_to_input_mapper.h \
            include/config/config.h \
            include/core/input_queue.h \
            include/core/roviz_item.h \
            include/core/roviz_item_p.h \
            include/core/strong_typedef.h \
            include/core/template_decl.h \
            include/core/template_decl_helpers.h \
            include/core/typedecl.h \
            include/gui/config_dialog.h \
            include/gui/dock_widget_signaling.h \
            include/gui/image_widget.h \
            include/gui/shared_window.h \
            include/gui/slider_label.h \
            include/streams/all_streams.h \
            include/streams/image.h \
            include/streams/image_m.h \
            include/streams/image_p.h \
            include/streams/message.h \
            include/streams/message_m.h \
            include/streams/message_p.h \
            include/streams/stream.h \
            include/streams/stream_object.h \
            include/streams/stream_object_p.h \
    include/config/cfg_double.h \
    include/config/cfg_int.h \
    include/config/cfg_string.h \
    include/config/cfg_bool.h \
    include/config/cfg_list.h \
    include/config/cfg_file_path.h \
    include/config/cfg_url.h

RESOURCES   +=  resources.qrc
LIBS        += -lopencv_core
