import React, { useEffect, useState } from 'react';

interface Item {
  id: number;
  name: string;
  value: number;
}

interface ApiResponse {
  items: Item[];
  count: number;
}

export const DataDisplay: React.FC = () => {
  const [data, setData] = useState<ApiResponse | null>(null);
  const [loading, setLoading] = useState<boolean>(true);
  const [error, setError] = useState<string | null>(null);

  useEffect(() => {
    const fetchData = async () => {
      try {
        const response = await fetch('http://localhost:3001/api/data');
        if (!response.ok) {
          throw new Error('Network response was not ok');
        }
        const data: ApiResponse = await response.json();
        setData(data);
        setLoading(false);
      } catch {
        setError('Failed to fetch data');
        setLoading(false);
      }
    };

    fetchData();
  }, []);

  if (loading) return <div>Loading...</div>;
  if (error) return <div>Error: {error}</div>;
  if (!data) return <div>No data available</div>;

  return (
    <div>
      <h2>Items from C++ Backend</h2>
      <p>Total items: {data.count}</p>
      <ul>
        {data.items.map((item) => (
          <li key={item.id}>
            {item.name}: {item.value}
          </li>
        ))}
      </ul>
    </div>
  );
};

export default DataDisplay;