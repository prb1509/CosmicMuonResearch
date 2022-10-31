import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

sns.set_theme()

def u_to_kg(mass):
    return mass / (6.022 * 10**26)

def J_to_eV(E):
    return E / e

def eV_to_J(E):
    return E * e

def scattering_angle(E,b):
    return 2 * np.arctan(e**2 / (8 * np.pi * epsilon * E * b))

def delta_v_ion(theta):
    return mu * (1 - np.cos(theta)) * (v_electron - v_ion)/ m_ion

def gamma(v):
    return 1 / np.sqrt(1 - v**2 / c**2)

#all physical constants
e = 1.6 / 10**19
c = 299752458
epsilon = 8.854 / 10**12
kB = 1.3806503 * 10**-23
k = e**2 / (4 * np.pi * epsilon)
h_bar = 1.054 / 10**34
m_electron = 9.11 / 10**31

T = 10 * 10**-3 #temperature of trap
E = eV_to_J(1e9) #median energy rounded up
omega = 10 * 10**6
m_ion = u_to_kg(173.04) #mass of Yb+
v_electron = np.sqrt(2 * E / m_electron) #nonrelativistic speed of electron, won't work for GeV energies
v_ion = np.sqrt(3 * kB * T / m_ion) 
mu = m_electron * m_ion / (m_electron + m_ion)
v_cm = (m_electron * v_electron + m_ion * v_ion) / (m_ion + m_electron)
b_omega = 2 * k / (v_electron * np.sqrt(2 * h_bar * m_ion * omega))
b_min = k / (mu * v_electron**2)
b = np.linspace(b_min,1000 * b_omega,100000)
theta = scattering_angle(E,b)
del_E = m_ion * v_cm * delta_v_ion(theta)

plt.figure(1)
plt.loglog(b,J_to_eV(del_E))
plt.axvline(b_min,color="black",linestyle="--",label="minimum b")
plt.axvline(b_omega,color="lime",linestyle="--",label="b calculated at frequency 10 MHz")
plt.xlabel("Impact Parameter (m)")
plt.ylabel("$\Delta$E (eV)")
plt.legend()

# plt.figure(2)
# plt.loglog(b,scattering_angle(E,b))
# plt.loglog(b,k / (gamma(v_electron) * m_electron * v_electron**2 * b))
# plt.xlabel("Impact Parameter (m)")
# plt.ylabel(r"$\theta$ (rad)")
# plt.legend(["General solution","Small angle solution"])
plt.show()