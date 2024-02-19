#!/bin/bash

mkdir -p build

glslc ./src/shader.vert -o build/vert.spv
glslc ./src/shader.frag -o build/frag.spv
