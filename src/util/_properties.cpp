#include "util/_properties.h"

const Property<bool> PROPERTIES::CYCLE("cycle", false);
const Property<vector<Edge *>> PROPERTIES::REVERSED("reversed", vector<Edge *>());
const Property<bool> PROPERTIES::CLEAN_SPL("clean_spl", false);
const Property<bool> PROPERTIES::CLEAN_DFF("clean_dff", false);
const Property<vector<vector<Node *>>> PROPERTIES::LAYERS("layers", vector<vector<Node *>>());
const Property<bool> PROPERTIES::PATH_BALANCED("path_balanced", false);
const Property<bool> PROPERTIES::EQ("cycle", false);