#pragma once
#ifndef OPENGM_SIMPLE_DISCRETE_SPACE_HXX
#define OPENGM_SIMPLE_DISCRETE_SPACE_HXX

#include "opengm/opengm.hxx"
#include "opengm/graphicalmodel/space/space_base.hxx"

namespace opengm {

/// Discrete space in which all variables have the same number of labels
template<class I = std::size_t, class L = std::size_t>
class SimpleDiscreteSpace
:  public SpaceBase<SimpleDiscreteSpace<I, L>, I, L> {
public:
   typedef I IndexType;
   typedef L LabelType;

   SimpleDiscreteSpace();
   SimpleDiscreteSpace(const IndexType, const IndexType);
   void assign(const IndexType, const IndexType);
   template<class Iterator> void assignDense(Iterator, Iterator);
   IndexType addVariable(const IndexType);
   IndexType numberOfVariables() const;
   IndexType numberOfLabels(const IndexType) const;
   bool isSimpleSpace() const ;

private:
   IndexType numberOfVariables_;
   IndexType numberOfLabels_;
};

template<class I, class L>
inline
SimpleDiscreteSpace<I, L>::SimpleDiscreteSpace()
:  numberOfVariables_(),
   numberOfLabels_()
{}

template<class I, class L>
inline
SimpleDiscreteSpace<I, L>::SimpleDiscreteSpace
(
   const IndexType numberOfVariables,
   const IndexType numberOfLabels
)
:  numberOfVariables_(numberOfVariables),
   numberOfLabels_(numberOfLabels)
{}

template<class I, class L>
template<class Iterator>
inline void
SimpleDiscreteSpace<I, L>::assignDense
(
   Iterator begin,
   Iterator end
) {
   numberOfVariables_ = std::distance(begin, end);
   numberOfLabels_ = static_cast<L>(*begin);
   while(begin != end) {
      if(numberOfLabels_ != static_cast<IndexType>(*begin)) {
         throw opengm::RuntimeError("*begin == SimpleDiscreteSpace.numberOfLabels_ is violated in SimpleDiscreteSpace::assignDense");
      }
      ++begin;
   }
}

template<class I, class L>
inline void
SimpleDiscreteSpace<I, L>::assign
(
   const IndexType numberOfVariables,
   const IndexType numberOfLabels
) {
   numberOfVariables_ = numberOfVariables;
   numberOfLabels_ = numberOfLabels;
}

template<class I, class L>
inline typename SimpleDiscreteSpace<I, L>::IndexType
SimpleDiscreteSpace<I, L>::addVariable
(
   const IndexType numberOfLabels
) {
   if(numberOfLabels != numberOfLabels_) {
      throw opengm::RuntimeError("numberOfLabels == SimpleDiscreteSpace.numberOfLabels_ is violated in SimpleDiscreteSpace::addVariable");
   }
   ++numberOfVariables_;
   return numberOfVariables_ - 1;
}

template<class I, class L>
inline typename SimpleDiscreteSpace<I, L>::IndexType
SimpleDiscreteSpace<I, L>::numberOfVariables() const {
   return numberOfVariables_;
}

template<class I, class L>
inline typename SimpleDiscreteSpace<I, L>::IndexType
SimpleDiscreteSpace<I, L>::numberOfLabels
(
   const IndexType dimension
) const {
   return numberOfLabels_;
}

template<class I, class L>
inline  bool
SimpleDiscreteSpace<I, L>::isSimpleSpace() const{
   return true;
}

} // namespace opengm

#endif // #ifndef OPENGM_SIMPLE_DISCRETE_SPACE_HXX
