//===--- Specifiers.h - Declaration and Type Specifiers ---------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief Defines various enumerations that describe declaration and
/// type specifiers.
///
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_BASIC_SPECIFIERS_H
#define LLVM_CLANG_BASIC_SPECIFIERS_H

#include "llvm/ADT/StringRef.h"

namespace clang {
  /// \brief Specifies the width of a type, e.g., short, long, or long long.
  enum TypeSpecifierWidth {
    TSW_unspecified,
    TSW_short,
    TSW_long,
    TSW_longlong
  };
  
  /// \brief Specifies the signedness of a type, e.g., signed or unsigned.
  enum TypeSpecifierSign {
    TSS_unspecified,
    TSS_signed,
    TSS_unsigned
  };
  
  /// \brief Specifies the kind of type.
  enum TypeSpecifierType {
    TST_unspecified,
    TST_void,
    TST_char,
    TST_wchar,        // C++ wchar_t
    TST_char16,       // C++0x char16_t
    TST_char32,       // C++0x char32_t
    TST_int,
    TST_int128,
    TST_half,         // OpenCL half, ARM NEON __fp16
    TST_float,
    TST_double,
    TST_bool,         // _Bool
    TST_decimal32,    // _Decimal32
    TST_decimal64,    // _Decimal64
    TST_decimal128,   // _Decimal128
    TST_enum,
    TST_union,
    TST_struct,
    TST_class,        // C++ class type
    TST_interface,    // C++ (Microsoft-specific) __interface type
    TST_typename,     // Typedef, C++ class-name or enum name, etc.
    TST_typeofType,
    TST_typeofExpr,
    TST_decltype,     // C++0x decltype
    TST_underlyingType, // __underlying_type for C++0x
    TST_auto,         // C++0x auto
    TST_unknown_anytype, // __unknown_anytype extension
    TST_atomic,       // C11 _Atomic
    // C++/CX extended types
    TST_ref_class,
    TST_ref_struct,
    TST_value_class,
    TST_value_struct,
    TST_interface_class,
    TST_interface_struct,
    TST_error         // erroneous type
  };
  
  /// \brief Structure that packs information about the type specifiers that
  /// were written in a particular type specifier sequence.
  struct WrittenBuiltinSpecs {
    /*DeclSpec::TST*/ unsigned Type  : 5;
    /*DeclSpec::TSS*/ unsigned Sign  : 2;
    /*DeclSpec::TSW*/ unsigned Width : 2;
    bool ModeAttr : 1;
  };  

  /// \brief A C++ access specifier (public, private, protected), plus the
  /// special value "none" which means different things in different contexts.
  enum AccessSpecifier {
    AS_public,
    AS_protected,
    AS_private,
    //C++/CLI extensions.
    AS_internal,
    AS_protected_public,
    AS_protected_private,
    AS_none
  };

  /// GetAccessSpecifierName - Converts from an access specifier enum to
  /// its string representation.
  inline llvm::StringRef GetAccessSpecifierName(AccessSpecifier AS) {
    switch(AS) {
    case AS_none:      return llvm::StringRef();
    case AS_public:    return "public";
    case AS_protected: return "protected";;
    case AS_private:   return "private";
    case AS_internal:  return "internal";
    case AS_protected_private: return "protected private";
    case AS_protected_public:  return "protected public";
    }
  }

  /// \brief The categorization of expression values, currently following the
  /// C++11 scheme.
  enum ExprValueKind {
    /// \brief An r-value expression (a pr-value in the C++11 taxonomy)
    /// produces a temporary value.
    VK_RValue,

    /// \brief An l-value expression is a reference to an object with
    /// independent storage.
    VK_LValue,

    /// \brief An x-value expression is a reference to an object with
    /// independent storage but which can be "moved", i.e.
    /// efficiently cannibalized for its resources.
    VK_XValue
  };

  /// \brief A further classification of the kind of object referenced by an
  /// l-value or x-value.
  enum ExprObjectKind {
    /// An ordinary object is located at an address in memory.
    OK_Ordinary,

    /// A bitfield object is a bitfield on a C or C++ record.
    OK_BitField,

    /// A vector component is an element or range of elements on a vector.
    OK_VectorComponent,

    /// An Objective-C property is a logical field of an Objective-C
    /// object which is read and written via Objective-C method calls.
    OK_ObjCProperty,
    
    /// An Objective-C array/dictionary subscripting which reads an
    /// object or writes at the subscripted array/dictionary element via
    /// Objective-C method calls.
    OK_ObjCSubscript
  };

  // \brief Describes the kind of template specialization that a
  // particular template specialization declaration represents.
  enum TemplateSpecializationKind {
    /// This template specialization was formed from a template-id but
    /// has not yet been declared, defined, or instantiated.
    TSK_Undeclared = 0,
    /// This template specialization was implicitly instantiated from a
    /// template. (C++ [temp.inst]).
    TSK_ImplicitInstantiation,
    /// This template specialization was declared or defined by an
    /// explicit specialization (C++ [temp.expl.spec]) or partial
    /// specialization (C++ [temp.class.spec]).
    TSK_ExplicitSpecialization,
    /// This template specialization was instantiated from a template
    /// due to an explicit instantiation declaration request
    /// (C++0x [temp.explicit]).
    TSK_ExplicitInstantiationDeclaration,
    /// This template specialization was instantiated from a template
    /// due to an explicit instantiation definition request
    /// (C++ [temp.explicit]).
    TSK_ExplicitInstantiationDefinition
  };

  /// \brief Storage classes.
  enum StorageClass {
    // These are legal on both functions and variables.
    SC_None,
    SC_Extern,
    SC_Static,
    SC_PrivateExtern,

    // These are only legal on variables.
    SC_OpenCLWorkGroupLocal,
    SC_Auto,
    SC_Register
  };

  /// \brief Checks whether the given storage class is legal for functions.
  inline bool isLegalForFunction(StorageClass SC) {
    return SC <= SC_PrivateExtern;
  }

  /// \brief Checks whether the given storage class is legal for variables.
  inline bool isLegalForVariable(StorageClass SC) {
    return true;
  }

  /// \brief In-class initialization styles for non-static data members.
  enum InClassInitStyle {
    ICIS_NoInit,   ///< No in-class initializer.
    ICIS_CopyInit, ///< Copy initialization.
    ICIS_ListInit  ///< Direct list-initialization.
  };
} // end namespace clang

#endif // LLVM_CLANG_BASIC_SPECIFIERS_H
