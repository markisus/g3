cc_library(
    name = "g3",
    srcs = [
	"add.h",
	"bivector.cpp",
	"multiply.h",
	"operators.cpp",
	"quaternion.cpp",
	"unroll_macro.h",
	"unrolled_add.h",
	"unrolled_multiply.h",
	"vector.cpp",
    ],
    hdrs = [
	"basis.h",
	"bivector.h",
	"bivector_layout.h",
	"g3.h",
	"multivector.h",
	"multivector_base.h",
	"multivector_layout.h",
	"operators.h",
	"quaternion.h",
	"quaternion_layout.h",
	"scalar.h",
	"vector.h",
	"vector_layout.h",
    ]
)

cc_binary(
    name = "benchmark",
    srcs = ["benchmark.cpp",
	    "multivector_layout.h",
	    "quaternion_layout.h",
	    "unroll_macro.h",
	    "unrolled_add.h",
	    "unrolled_multiply.h",
	    "vector_layout.h",
    ],
    deps = [":g3"]
)

cc_binary(
    name = "test",
    srcs = ["test.cpp"],
    deps = [":g3"]
)
