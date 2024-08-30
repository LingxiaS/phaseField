#ifndef INCLUDE_EQUATIONDEPENDECYPARSER_H_
#define INCLUDE_EQUATIONDEPENDECYPARSER_H_

#include "varTypeEnums.h"

#include <algorithm>
#include <string>
#include <vector>

/**
 * This is a class to parse the strings the user puts into the
 * variableAttributeLoader to specify which variable values, gradients,
 * hessians, etc are needed for each governing equation.
 */
class EquationDependencyParser
{
public:
  void
  parse(std::vector<std::string> var_name,
        std::vector<PDEType>     var_eq_type,
        std::vector<std::string> sorted_dependencies_value_RHS,
        std::vector<std::string> sorted_dependencies_gradient_RHS,
        std::vector<std::string> sorted_dependencies_value_LHS,
        std::vector<std::string> sorted_dependencies_gradient_LHS,
        std::vector<bool>       &var_nonlinear);

  void
  pp_parse(std::vector<std::string> var_name,
           std::vector<std::string> pp_var_name,
           std::vector<std::string> sorted_dependencies_value,
           std::vector<std::string> sorted_dependencies_gradient);

  // All of the vectors of flags for what is needed for the solution variables
  std::vector<bool> need_value_explicit_RHS;
  std::vector<bool> need_gradient_explicit_RHS;
  std::vector<bool> need_hessian_explicit_RHS;

  std::vector<bool> need_value_nonexplicit_RHS;
  std::vector<bool> need_gradient_nonexplicit_RHS;
  std::vector<bool> need_hessian_nonexplicit_RHS;

  std::vector<bool> need_value_nonexplicit_LHS;
  std::vector<bool> need_gradient_nonexplicit_LHS;
  std::vector<bool> need_hessian_nonexplicit_LHS;

  std::vector<bool> need_value_change_nonexplicit_LHS;
  std::vector<bool> need_gradient_change_nonexplicit_LHS;
  std::vector<bool> need_hessian_change_nonexplicit_LHS;

  std::vector<bool> need_value_residual_explicit_RHS;
  std::vector<bool> need_gradient_residual_explicit_RHS;

  std::vector<bool> need_value_residual_nonexplicit_RHS;
  std::vector<bool> need_gradient_residual_nonexplicit_RHS;

  std::vector<bool> need_value_residual_nonexplicit_LHS;
  std::vector<bool> need_gradient_residual_nonexplicit_LHS;

  // All of the vectors of flags for what is needed for the postprocessing
  // variables
  std::vector<bool> pp_need_value;
  std::vector<bool> pp_need_gradient;
  std::vector<bool> pp_need_hessian;

  std::vector<bool> pp_need_value_residual;
  std::vector<bool> pp_need_gradient_residual;

protected:
  /*
   * Method to strip excess whitespace for the dependency lists
   */
  void
  strip_dependency_whitespace(std::string &dependency_list);

  /**
   * Method to parse the RHS dependency strings and populate the vectors for
   * whether values, gradients, or hessians are needed.
   */
  void
  parseDependencyListRHS(std::vector<std::string> variable_name_list,
                         std::vector<PDEType>     variable_eq_type,
                         unsigned int             variable_index,
                         std::string              value_dependencies,
                         std::string              gradient_dependencies,
                         std::vector<bool>       &need_value,
                         std::vector<bool>       &need_gradient,
                         std::vector<bool>       &need_hessian,
                         bool                    &need_value_residual,
                         bool                    &need_gradient_residual,
                         bool                    &is_nonlinear);

  /**
   * Method to parse the LHS dependency strings and populate the vectors for
   * whether values, gradients, or hessians are needed.
   */
  void
  parseDependencyListLHS(std::vector<std::string> var_name,
                         std::vector<PDEType>     var_eq_type,
                         unsigned int             var_index,
                         std::string              value_dependencies,
                         std::string              gradient_dependencies,
                         std::vector<bool>       &need_value,
                         std::vector<bool>       &need_gradient,
                         std::vector<bool>       &need_hessian,
                         std::vector<bool>       &need_value_change,
                         std::vector<bool>       &need_gradient_change,
                         std::vector<bool>       &need_hessian_change,
                         bool                    &need_value_residual,
                         bool                    &need_gradient_residual,
                         bool                    &is_nonlinear);

  /**
   * Method to parse the postprocessing dependency strings and populate the
   * vectors for whether values, gradients, or hessians are needed.
   */
  void
  parseDependencyListPP(std::vector<std::string> var_name,
                        std::string              value_dependencies,
                        std::string              gradient_dependencies,
                        std::vector<bool>       &need_value,
                        std::vector<bool>       &need_gradient,
                        std::vector<bool>       &need_hessian,
                        bool                    &need_value_residual,
                        bool                    &need_gradient_residual);
};

#endif
