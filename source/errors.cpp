#include "errors.hpp"

ShellError::~ShellError()
= default;

ParseError::ParseError(char *message) : ShellError(message) {
}

ParseError::~ParseError()
= default;


InterpretError::InterpretError(char *message) : ShellError(message) {
}

InterpretError::~InterpretError()
= default;

AssignmentInterpretError::AssignmentInterpretError(char *message) : InterpretError(message) {
}

AssignmentInterpretError::~AssignmentInterpretError()
= default;

AssignmentNameInterpretError::AssignmentNameInterpretError(char *message) : AssignmentInterpretError(message) {
}

AssignmentNameInterpretError::~AssignmentNameInterpretError()
= default;

MemoryAssignmentInterpretError::MemoryAssignmentInterpretError(char *message) : AssignmentInterpretError(message) {
}

MemoryAssignmentInterpretError::~MemoryAssignmentInterpretError()
= default;