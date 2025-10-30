const DUMMY_DATA = [
    { id: 101, name: "Project Alpha", status: "Active" },
    { id: 102, name: "Task Beta", status: "Pending" },
    { id: 103, name: "Report Gamma", status: "Completed" },
    { id: 104, name: "Ticket Delta", status: "Blocked" },
];

fetch("http://localhost:1026/v2/entities", { method: "GET" })
    .then((response) => {
        return response.json();
    })
    .then((data) => {
        console.log(data);
    })
    .catch((error) => {
        console.error("Logout failed (placeholder):", error);
    });

function renderTable(data) {
    const tbody = document.getElementById("data-table-body");
    tbody.innerHTML = "";

    data.forEach((item) => {
        const row = tbody.insertRow();
        row.insertCell().textContent = item.id;
        row.insertCell().textContent = item.name;
        row.insertCell().textContent = item.status;

        const actionCell = row.insertCell();
        actionCell.innerHTML = `
            <button class="action-btn edit-btn" onclick="handleEdit(${item.id})">Edit</button>
            <button class="action-btn delete-btn" onclick="handleDelete(${item.id})">Delete</button>
        `;
    });
}

function handleLogout() {
    // Placeholder: Simulate API call to destroy session
    console.log("Attempting to log out...");

    fetch("/api/logout", { method: "POST" })
        .then((response) => {
            console.log("Logout successful (placeholder)");
            // Redirect to the login page after successful logout
            window.location.href = "/login";
        })
        .catch((error) => {
            console.error("Logout failed (placeholder):", error);
        });
}

function handleAddItem() {
    // Placeholder: Data you would normally gather from a modal/form
    const newItem = {
        name: "New Entry",
        status: "Draft",
        description: "Placeholder data",
    };

    console.log("Attempting to add new item:", newItem);

    // Placeholder: Replace this URL and payload with your actual API endpoint
    fetch("/api/items", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify(newItem),
    })
        .then((response) => response.json())
        .then((data) => {
            console.log(
                "Add item successful (placeholder). New item ID:",
                data.id
            );
            // In a real app, you would refresh the table data here
        })
        .catch((error) =>
            console.error("Add item failed (placeholder):", error)
        );
}

function handleEdit(id) {
    // Placeholder: You would fetch the item data, show a form, and then submit
    const updatedData = { name: `Edited Item ${id}`, status: "Updated" };

    console.log(`Attempting to edit item ID ${id} with data:`, updatedData);

    // Placeholder: Replace this URL and payload with your actual API endpoint
    fetch(`/api/items/${id}`, {
        method: "PUT", // or PATCH
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify(updatedData),
    })
        .then((response) => response.json())
        .then((data) => {
            console.log(`Edit successful (placeholder) for item ID ${id}`);
            // In a real app, update the row visually
        })
        .catch((error) => console.error("Edit failed (placeholder):", error));
}

function handleDelete(id) {
    // Placeholder: You would normally confirm deletion first
    console.log(`Attempting to delete item ID ${id}`);

    // Placeholder: Replace this URL with your actual API endpoint
    fetch(`/api/items/${id}`, {
        method: "DELETE",
    })
        .then((response) => {
            if (response.ok) {
                console.log(
                    `Delete successful (placeholder) for item ID ${id}`
                );
                // In a real app, remove the row from the table
            } else {
                console.error(`Delete failed (placeholder) for item ID ${id}`);
            }
        })
        .catch((error) => console.error("Delete failed (placeholder):", error));
}

document.addEventListener("DOMContentLoaded", () => {
    renderTable(DUMMY_DATA);
});
