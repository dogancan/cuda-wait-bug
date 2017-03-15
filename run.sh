#!/bin/bash

set -e

( ./wait-for-gpu &> log.1 ) &

sleep 3

( ./wait-for-gpu &> log.2 ) &

wait
