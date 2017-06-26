#include <strategies/input/naiveBasicInputInitialLoad.h>

const BasicInput::SetOfId NaiveBasicInputInitialLoad::getAllKeysFromLoadMap(const LoadMap &loadMap) const {
  BasicInput::SetOfId retVal = BasicInput::SetOfId();

  for(auto const& element : loadMap)
    retVal.push_back(element.first);

  return retVal;
}

const BasicInput::Load &NaiveBasicInputInitialLoad::getPELoad(const Id &PEId) const {
  auto mapIt = _PEs.find(PEId);

  if(mapIt == _PEs.end()) {
    throw Error::INVALID_INPUT_ACCESS;
  }

  return mapIt->second;
}

const BasicInput::SetOfId &NaiveBasicInputInitialLoad::getPEs() const {
  return _PEsIds;
}