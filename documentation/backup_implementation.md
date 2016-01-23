# Backup Implementation Documentation

**Authors:** Jayden Navarro, Coy Humphrey

**Purpose:** Describes the implementation of our backup solution.

## Overview

We use rsync to backup all important files on our main disk to a backup disk. We run a backup script to perform a diff backup from our primary drive onto our secondary backup drive.

## Implementation Steps

### Formatting Backup Drive

### Mounting Backup Drive

### Running Backup

### Running Repair from Backup

### Scripts

## Initial Implementation Steps

We ran into issues mounting the secondary drive, but were able to solve this by partitioning 
