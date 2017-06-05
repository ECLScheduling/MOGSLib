#include <lb/input/naiveBasicInputInitialLoad.h>

const BasicInput::SetOfId NaiveBasicInputInitialLoad::getAllKeysFromLoadMap(const LoadMap &loadMap) const {
  BasicInput::SetOfId retVal = BasicInput::SetOfId();

  for(auto const& element : loadMap)
    retVal.insert(element.first);

  return retVal;
}

const BasicInput::Load &NaiveBasicInputInitialLoad::getPELoad(const Id &peId) const {
  auto mapIt = _PEs.find(peId);

  if(mapIt == _PEs.end()) {
    throw Error::INVALID_INPUT_ACCESS;
  }

  return mapIt->second;
}

const BasicInput::SetOfId &NaiveBasicInputInitialLoad::getPEsIds() const {
  return _PEsIds;
}