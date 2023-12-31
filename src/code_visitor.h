#ifndef OD_VISITOR_H
#define OD_VISITOR_H

#include <map>

#include "errors.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"

// Forward declare
class IntLiteralExpr;
class StringLiteralExpr;
class BoolLiteralExpr;
class DoubleLiteralExpr;
class UnaryExpr;
/* class NilLiteralExpr; */
class BinaryExpr;
class VariableExpr;
class Expression;
class VariableStmt;

class CodeVisitor {
   public:
    std::unique_ptr<llvm::LLVMContext> TheContext;
    std::unique_ptr<llvm::IRBuilder<>> Builder;
    std::unique_ptr<llvm::Module> TheModule;
    std::map<std::string, llvm::Value *> NamedValues;
    CodeVisitor() noexcept;
    // inherited from Expr
    llvm::Value *VisitIntLiteral(IntLiteralExpr &);
    llvm::Value *VisitStringLiteral(StringLiteralExpr &);
    llvm::Value *VisitDoubleLiteral(DoubleLiteralExpr &);
    llvm::Value *VisitBoolLiteral(BoolLiteralExpr &);
    llvm::Value *VisitUnaryExpr(UnaryExpr &);
    llvm::Value *VisitBinaryExpr(BinaryExpr &);
    llvm::Value *VisitVariableExpr(VariableExpr &);
    /* llvm::Value *VisitNilLiteralExpr(NilLiteralExpr &); */
    // inherited from Stmt
    llvm::Value *VisitVariableStmt(VariableStmt &);
    llvm::Value *VisitExpression(Expression &);

    std::vector<struct Diagnostic> diagnostics_;
    void report_error_(std::string message, int line, size_t starts_at,
                       size_t ends_at);
    bool had_error_somewhere;
};

#endif
