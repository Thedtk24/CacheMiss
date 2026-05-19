import os
import pandas as pd
import matplotlib.pyplot as plt

base_dir = '..'
input_dir = os.path.join(base_dir, 'reports', 'raw')
output_dir = os.path.join(base_dir, 'reports', 'figures')

os.makedirs(output_dir, exist_ok=True)

try:
    df_O0 = pd.read_csv(os.path.join(input_dir, 'results_O0.csv'))
    df_O2 = pd.read_csv(os.path.join(input_dir, 'results_O2.csv'))
except FileNotFoundError as e:
    print(f"Error: {e}")
    exit()

df0_mean = df_O0.groupby('size').mean().reset_index()
df2_mean = df_O2.groupby('size').mean().reset_index()

df0_mean['ratio'] = df0_mean['col_ms'] / df0_mean['row_ms']
df2_mean['ratio'] = df2_mean['col_ms'] / df2_mean['row_ms']

fig, ax = plt.subplots(figsize=(10, 6))

ax.plot(df0_mean['size'], df0_mean['row_ms'], 'o-',  label='O0 - row',    color='tab:blue',   linewidth=2)
ax.plot(df0_mean['size'], df0_mean['col_ms'], 's--', label='O0 - column', color='tab:cyan',   linewidth=2)
ax.plot(df2_mean['size'], df2_mean['row_ms'], 'v-',  label='O2 - row',    color='tab:red',    linewidth=2)
ax.plot(df2_mean['size'], df2_mean['col_ms'], '^--', label='O2 - column', color='tab:orange', linewidth=2)

ax.set_xlabel('Matrix size ($N \\times N$)', fontsize=12)
ax.set_ylabel('Running time (ms)', fontsize=12)
ax.set_title('Performance comparison: O0 vs O2 (row vs column)', fontsize=14, fontweight='bold')
ax.set_xticks(df0_mean['size'])
ax.set_xticklabels(df0_mean['size'])
ax.grid(True, which='both', ls='--', alpha=0.5)
ax.legend(fontsize=11, loc='upper left')

plt.tight_layout()
plt.savefig(os.path.join(output_dir, 'comparison_O0_O2.png'), dpi=300)
print("Graph 1 saved: comparison_O0_O2.png")

fig, ax = plt.subplots(figsize=(10, 6))

ax.plot(df0_mean['size'], df0_mean['ratio'], 'o-', label='O0', color='tab:blue',   linewidth=2)
ax.plot(df2_mean['size'], df2_mean['ratio'], 's-', label='O2', color='tab:orange', linewidth=2)
ax.axhline(y=1.0, color='gray', linestyle='--', linewidth=1, label='ratio = 1 (equal)')

ax.set_xlabel('Matrix size ($N \\times N$)', fontsize=12)
ax.set_ylabel('Slowdown ratio (col / row)', fontsize=12)
ax.set_title('Column-major slowdown relative to row-major', fontsize=14, fontweight='bold')
ax.set_xticks(df0_mean['size'])
ax.set_xticklabels(df0_mean['size'])
ax.grid(True, which='both', ls='--', alpha=0.5)
ax.legend(fontsize=11)

plt.tight_layout()
plt.savefig(os.path.join(output_dir, 'ratio_col_over_row.png'), dpi=300)
print("Graph 2 saved: ratio_col_over_row.png")