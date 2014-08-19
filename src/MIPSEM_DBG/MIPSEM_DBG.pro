QT += widgets

SOURCES += \
    main.cpp \
    MIPSEM_CORE/Assembler.cpp \
    MIPSEM_CORE/BitManip.cpp \
    MIPSEM_CORE/BitResolver.cpp \
    MIPSEM_CORE/Core.cpp \
    MIPSEM_CORE/CPU.cpp \
    MIPSEM_CORE/Decoder.cpp \
    MIPSEM_CORE/Encoder.cpp \
    MIPSEM_CORE/Exceptions.cpp \
    MIPSEM_CORE/Instruction.cpp \
    MIPSEM_CORE/InstructionData.cpp \
    MIPSEM_CORE/InstructionDataBank.cpp \
    MIPSEM_CORE/Literals.cpp \
    MIPSEM_CORE/MemoryMap.cpp \
    MIPSEM_CORE/Parser.cpp \
    MIPSEM_CORE/StringResolver.cpp \
    MIPSEM_CORE/VirtualMemory.cpp

HEADERS += \
    MIPSEM_CORE/Assembler.hpp \
    MIPSEM_CORE/BitManip.hpp \
    MIPSEM_CORE/BitResolver.hpp \
    MIPSEM_CORE/Core.hpp \
    MIPSEM_CORE/CPU.hpp \
    MIPSEM_CORE/Decoder.hpp \
    MIPSEM_CORE/Encoder.hpp \
    MIPSEM_CORE/Exceptions.hpp \
    MIPSEM_CORE/Instruction.hpp \
    MIPSEM_CORE/InstructionData.hpp \
    MIPSEM_CORE/InstructionDataBank.hpp \
    MIPSEM_CORE/Literals.hpp \
    MIPSEM_CORE/MemoryMap.hpp \
    MIPSEM_CORE/Parser.hpp \
    MIPSEM_CORE/StringResolver.hpp \
    MIPSEM_CORE/types.hpp \
    MIPSEM_CORE/VirtualMemory.hpp
