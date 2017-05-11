#!/bin/bash
sem -j+0 ./spatial_locality ycsb > ycsb_spatial_locality;
sem -j+0 ./spatial_locality tpcq6 > tpcq6_spatial_locality;
sem --wait

