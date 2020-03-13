#!/bin/bash
grep -o -i "{" test.c | wc -l
grep -o -i "}" test.c | wc -l
