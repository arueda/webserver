cc_library(
    name = "Session",
    srcs = ["Session.cc"],
    hdrs = ["Session.h"],
    deps = [
        "@boost//:asio_ssl",
        "@boost//:beast",
    ],
)

cc_library(
    name = "Listener",
    srcs = ["Listener.cc"],
    hdrs = ["Listener.h"],
    deps = [
        ":Session",
        "@boost//:asio_ssl",
        "@boost//:beast",
    ],
)

cc_binary(
    name = "webserver",
    srcs = [
         "main.cc"
    ],
    deps = [
        ":Listener",
        "@boost//:asio_ssl",
        "@boost//:beast",
    ],
)
