#include "util/_properties.h"

const Property<bool> PROPERTIES::REVERSED("reversed", false);
const Property<vector<pair<Node *, Node *>>> PROPERTIES::CYCLE("cycle", vector<pair<Node *, Node *>>());
const Property<bool> PROPERTIES::CLEAN_SPL("clean_spl", false);
const Property<bool> PROPERTIES::CLEAN_DFF("clean_dff", false);
const Property<vector<vector<Node *>>> PROPERTIES::LAYERS("layers", vector<vector<Node *>>());
const Property<bool> PROPERTIES::PATH_BALANCED("path_balanced", false);
const Property<bool> PROPERTIES::EQ("cycle", false);