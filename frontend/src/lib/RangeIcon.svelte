<script lang="ts">
  export let undefinedIcon: string;
  export let icons: string[];
  export let min: number;
  export let max: number;
  export let value: number | undefined | null;
  export let displayValue: string;
</script>

<img
  src={value === undefined || value === null
    ? undefinedIcon
    : icons[
        Math.round(
          ((icons.length - 1) * Math.max(min, Math.min(max, value) - min)) /
            (max - min)
        )
      ]}
  alt={displayValue}
  title={displayValue}
  data-tooltip={displayValue}
/>
