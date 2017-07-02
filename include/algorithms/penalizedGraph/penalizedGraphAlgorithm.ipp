// #############################################
// Implementation of the PenalizedGraphAlgorithm template methods.
// #############################################

template<typename Weight>
const Weight PenalizedGraphAlgorithm<Weight>::totalWeightGraph(const Weight &vWeightSum, const unsigned int &vSize) const {
  return vWeightSum + penalityFunction(vSize);
}

template<typename Weight>
const Weight PenalizedGraphAlgorithm<Weight>::weightUnion(const Weight &vSumA, const Weight &vSumB, const unsigned int &vSizeA, const unsigned int &vSizeB) const {
  const Weight sum = totalWeightGraph(vSumA, vSizeA) + totalWeightGraph(vSumB, vSizeB);
  const Weight penality = penalityFunction(vSizeA + vSizeB) - penalityFunction(vSizeA) - penalityFunction(vSizeB);
    
  return sum + penality; 
}

template<typename Weight>
const Weight PenalizedGraphAlgorithm<Weight>::weightIncrementalLoseAVertex(const Weight &curWeight, const unsigned int &vSize, const Weight &vWeight) const {   
  return curWeight - vWeight - penalityFunction(vSize) + penalityFunction(vSize-1);
}

template<typename Weight>
const Weight PenalizedGraphAlgorithm<Weight>::weightIncrementalGainAVertex(const Weight &curWeight, const unsigned int &vSize, const Weight &vWeight) const {
  return curWeight - vWeight - penalityFunction(vSize) + penalityFunction(vSize+1);
}