import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import solve_ivp

# Given values
R = 10e3  # 10 kΩ
C = 25e-6  # 25 µF
I_0 = 2e-3  # 2 mA (step current input)
tau = R * C  # Time constant

# Time range for simulation
t_max = 5 * tau  # Simulate for 5 time constants
t_eval = np.linspace(0, t_max, 1000)  # Time steps for numerical solution

# Differential equation for Vc (capacitor voltage)
def rc_circuit(t, Vc):
    dV_dt = (I_0 - Vc / R) / C  # Derived from KCL
    return dV_dt

# Initial condition (Vc(0) = 0)
Vc_0 = [0]

# Solve the ODE
solution = solve_ivp(rc_circuit, [0, t_max], Vc_0, t_eval=t_eval, method='RK45')

# Plot the step response
plt.figure(figsize=(8, 5))
plt.plot(solution.t, solution.y[0], label='$V_c(t)$ (Capacitor Voltage)', color='b')
plt.axhline(I_0 * R, linestyle="--", color='r', label='$V_c(\infty) = I_0 R$')
plt.xlabel("Time (s)")
plt.ylabel("Voltage (V)")
plt.title("Step Response of the Parallel RC Circuit")
plt.legend()
plt.grid()
plt.show()