#code to analyse the muon simulations
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np
import pandas as pd
import csv
import os

sns.set_theme()

def count_unique_particles(df,particle_type=None):
    """Function to count number of unique particles for a given event.
    
    Parameters:
    
    df - Pandas DataFrame
    
    Dataframe object containg data of events.
    
    particle_type - str

    Name of particle. If no type is given, then function counts all unique particles 
    of all types for given event.
    See Particle_List.txt for list of valid names.

    Returns integer value of total counts.
    """

    #if particle type is not given function acts on entire dataset
    if particle_type is None:
        df_particle = df
    else:
        df_particle = df[df["ParticleType"] == particle_type]

    return len(df_particle.groupby(["Event","trackID"]))

def edit_csv_headers(file):
    """Function to edit csv file headers.
    Geant4's G4CsvAnalysisManager returns csv files of ntuples in a form where the headers are placed row-wise
    in the following format:

    #class tools::wcsv::ntuple	

    #title "title"	

    #separator 44	

    #vector_separator 59	

    #column "data type" "column name"

    Parameters:

    file -  str, file-like

    File or file path	

    Returns None. Writes new file in directory of old file.
    """

    #we create a new csv file to write to 
    new_filename = file.split(".")[0] + "_modified.csv"

    #headers list
    headers = []

    #start reading and writing
    with open(file,newline="") as old, open(new_filename,"w",newline="") as new:
        r = csv.reader(old)
        w = csv.writer(new)

        #we skip the first 4 lines which are constant between each file
        for i in range(4):
            next(r,None)

        #get headers
        for row in r:
            if row[0][0] == "#":
                unsplit = row[0].strip("#column ")
                headers.append(unsplit.split(" ")[-1])
            else: 
                break

        #write the headers
        w.writerow(headers)

        #copy and write everything else; ie, all the data
        for row in r:
            if row[0][0] != "#":
                w.writerow(row)
            else:
                raise ValueError("Encoutered header where data was expected.")

def get_unique_column(df,col_idx):
    """Function to get all unique values of column(s) of data frame.
    
    Parameters:
    
    df - Pandas DataFrame
    
    Dataframe object containg data of events.
    
    col_idx - int, float, arraylike
    
    Index of column to pull values from. Can pass array containing 
    multiple indices.
    
    Returns numpy array containing unique values."""
    return pd.unique(df[df.columns[col_idx]])    

def plot_energy_dist(df,particle_type,material,key=None):
    """Plots energy distribution of given particle type.
    
    Parameters:
    
    df - Pandas DataFrame
    
    Dataframe object containg data of events.

    particle_type - str, int, float

    Type of particle. If no key is passed,
    it is assumed the type is its name.
    See Particle_List.txt for list of valid names.
    By passing a valid key, other parameters, say charge, mass etc can be passed here.
    
    material - str

    Type of material of outer layer.

    key - str
    Column name for particle identifier. Defaults to ParticleType.
    
    Returns plotted data."""

    if key is None:
        key = "ParticleType"

    charge_dict = {-1:"electron",1:"positron"}
    df_particle = df[df[key] == particle_type]
    KE = df_particle["Energy_(MeV)"]
    # print(np.mean(KE))
    print(np.median(KE))
    # print(np.min(KE))
    # print(np.percentile(KE,25))
    # print(np.percentile(KE,75))
    plt.hist((KE),100,range=(np.min(KE),np.percentile(KE,85)))
    plt.title("Energy distribution of " + charge_dict[particle_type] + "s ({})".format(material) )
    plt.xlim(left=-np.min(KE))
    plt.xticks(np.arange(0,round(np.percentile(KE,85)) + 1,5))
    plt.xlabel("(Energy) / MeV")
    plt.ylabel("Count")
    plt.show()

def plot_num_particles(df,material,particle=None):
    """Function to plot distribution of particle counts.
    
    Parameters:

    df - Pandas DataFrame
    
    Dataframe object containg data of events.

    material - str

    Type of material of outer layer.

    particle - str, int, float

    Type of particle. If no key is passed,
    it is assumed the type is its name.
    See Particle_List.txt for list of valid names.
    By passing a valid key, other parameters, say charge, mass etc can be passed here.
    
    key - str
    Column name for particle identifier. Defaults to ParticleType.
    
    Returns plotted data."""

    if particle is not None:
        #confidence interval of distribution of given particle
        plt.boxplot(df[df["particle"] == particle]["count"])
        plt.xticks([])
        plt.ylabel("Counts")
        plt.title("Distribution of counts for {} ({})".format(particle,material))
        plt.show()
    else:
        #lineplot of distributions of all particles in dataset
        sns.lineplot(x="run",y="count",hue="particle",data=df).set_title("Secondary particle count distribution ({})".format(material))
        plt.show()

def main(prefix,files=50):

    num_files = files
    runs = [i for i in range(num_files)]
    df = pd.DataFrame()
    data = []

    for file in range(num_files):
        #assumes Muon_data folder is located in the current directory; ie, is a subdirectory
        filename = os.getcwd() +  r"\Muon_data\{}\{}{}_nt_Hits.csv".format(prefix,prefix,file)
        new_filename = os.getcwd() + r"\Muon_data\{}\{}{}_nt_Hits{}.csv".format(prefix,prefix,file,"_modified")

        #write new files only if they don't exist
        if not os.path.exists(new_filename):
            edit_csv_headers(filename)
        
        df_new = pd.read_csv(new_filename)
        df_new["run"] = file
        #create dataframe containing the information in the csv: positions, energy etc
        #we group by event and trackID since for every event the trackID is a unique identifier
        df  = pd.concat([df,df_new.groupby(["Event","trackID"]).mean()])
        
        #we create two dictionaries keeping track of electrons and protons 
        #produced for each run and append these to the data array
        e_dict = {}
        p_dict = {}
        p_dict.update({"count":count_unique_particles(df_new,"e+"),"particle":"e+"})
        data.append(p_dict)
        e_dict.update({"count":count_unique_particles(df_new,"e-"),"particle":"e-"})
        data.append(e_dict)

    #create dataframe of particle counts
    tot_particles = pd.DataFrame(data)
    tot_particles["run"] = [i for i in runs for j in range(2)]

    #plot
    plot_num_particles(tot_particles,prefix,"e-")
    plot_num_particles(tot_particles,prefix,"e+")
    plot_num_particles(tot_particles,prefix)
    plot_energy_dist(df,-1,prefix,key="charge_(e+)")
    plot_energy_dist(df,1,prefix,key="charge_(e+)")

main("Results")