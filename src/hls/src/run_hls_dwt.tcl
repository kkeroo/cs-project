#
# Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
# Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Create a project
open_project proj -reset

# Add design files
add_files ../src/dwt.cpp



# Set the top-level function
set_top dwt

# ########################################################
# Create a solution
open_solution solution -reset 

# Define technology and clock rate
set_part {xcu250-figd2104-2L-e}
create_clock -period 10 -name default

# Set variable to select which steps to execute
set hls_exec 1


#synthesise desing and obtain results 
csynth_design



exit