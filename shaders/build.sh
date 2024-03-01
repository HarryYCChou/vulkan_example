#!/bin/bash

mkdir -p build

glslc ./src/shader.vert -o build/vert.spv
glslc ./src/shader.frag -o build/frag.spv
glslc ./src/shader_2.vert -o build/vert_2.spv
glslc ./src/shader_2.frag -o build/frag_2.spv
