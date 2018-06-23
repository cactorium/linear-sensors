#!/bin/sh

zip "../capacitive_scale-$(git rev-parse --short HEAD).zip" -xi capacitive-scale-gerber/*
