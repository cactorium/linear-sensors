#!/bin/sh

zip "../capacitive_$(git rev-parse --short HEAD).zip" -xi capacitive-gerber/*
