#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed May 23 15:24:05 2018

@author: Mely
"""

import numpy as np

def split(files, idxs):
    n_train = int(len(files)*0.6)
    n_val = int(len(files)*0.2)
    train = [files[i] for i in idxs[:n_train]]
    val = [files[i] for i in idxs[n_train:n_train+n_val]]
    test = [files[i] for i in idxs[n_train+n_val:]]
    return train, val, test

def save(file, *sets):
    with open(file,'w') as writer:
        for set_n in sets:
            for line in set_n:
                writer.write(line+'\n')

main_dir = '/Users/Mely/Documents/School/FIMEE/6to semestre/Minería de Datos/Data/imagenes/files/'
files_file = main_dir+'images.txt'

files_train = main_dir+'files_train.txt'
files_val = main_dir+'files_val.txt'
files_test = main_dir+'files_test.txt'

labels_train_file = main_dir+'labels_train.txt'
labels_val_file = main_dir+'labels_val.txt'
labels_test_file = main_dir+'labels_test.txt'

files_dog = []
files_cat = []
files_rab = []
with open(files_file,'r') as reader:
    for line in reader:
        words = line.split('_')
        if words[1] == 'perro':
            files_dog.append(line.rstrip())
        elif words[1] == 'gato':
            files_cat.append(line.rstrip())
        else:
            files_rab.append(line.rstrip())

idxs_dog = list(range(len(files_dog)))
idxs_cat = list(range(len(files_cat)))
idxs_rab = list(range(len(files_rab)))
idxs_dog = np.random.permutation(idxs_dog)
idxs_cat = np.random.permutation(idxs_cat)
idxs_rab = np.random.permutation(idxs_rab)

train_dog, val_dog, test_dog = split(files_dog,idxs_dog)
train_cat, val_cat, test_cat = split(files_cat,idxs_cat)
train_rab, val_rab, test_rab = split(files_rab,idxs_rab)

save(files_train, train_dog, train_cat, train_rab)
save(files_val, val_dog, val_cat, val_rab)
save(files_test, test_dog, test_cat, test_rab)

save(labels_train_file,['perro']*len(train_dog),['gato']*len(train_cat),['conejo']*len(train_rab))
save(labels_val_file,['perro']*len(val_dog),['gato']*len(val_cat),['conejo']*len(val_rab))
save(labels_test_file,['perro']*len(test_dog),['gato']*len(test_cat),['conejo']*len(test_rab))